module GetCrops = [%graphql
  {|
query AllCrops {
  allCrops(orderBy: NAME_ASC) {
    nodes {
      name
      id
      category
      season
    }
  }
}
|}
];

module GetCropsQuery = ReasonApolloHooks.Query.Make(GetCrops);

type state = {
  category: option(Crop.Category.t),
  search: option(string),
  season: option(int),
};

type action =
  | Category(option(Crop.Category.t))
  | InSeason
  | Search(option(string))
  | Reset;

[@react.component]
let make = () => {
  let (result, _full) = GetCropsQuery.use();
  let initialState = {category: None, search: None, season: None};

  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Category(category) => {...state, category}
        | InSeason => {
            ...state,
            season: Some(Js.Date.make() |> Js.Date.getMonth |> int_of_float),
          }
        | Search(search) => {...state, search}
        | Reset => initialState
        },
      initialState,
    );

  switch (result) {
  | Error(_)
  | NoData
  | Loading => React.null
  | Data(response) =>
    <Layout>
      <input
        className="bg-white w-full rounded px-4 py-2 shadow-md mb-10"
        onChange={event => {
          let value = event->ReactEvent.Form.target##value;

          switch (value) {
          | "" => dispatch(Search(None))
          | value => dispatch(Search(Some(value)))
          };
        }}
        placeholder={j|Hitta frukt eller grönsak|j}
        type_="text"
      />
      <div className="mb-10">
        <Pill
          isSelected={
            switch (state.category) {
            | Some(`FRUIT) => true
            | Some(`VEGETABLE)
            | None => false
            }
          }
          onClick={_ => dispatch(Category(Some(`FRUIT)))}>
          {React.string("Frukt")}
        </Pill>
        <Pill
          isSelected={
            switch (state.category) {
            | Some(`VEGETABLE) => true
            | Some(`FRUIT)
            | None => false
            }
          }
          onClick={_ => dispatch(Category(Some(`VEGETABLE)))}>
          {React.string({j|Grönsaker|j})}
        </Pill>
        <Pill
          isSelected={
            switch (state.season) {
            | Some(_) => true
            | None => false
            }
          }
          onClick={_ => dispatch(InSeason)}>
          {React.string({j|I säsong|j})}
        </Pill>
        {switch (state.category, state.season) {
         | (_, Some(_))
         | (Some(_), _) =>
           <button
             className="text-sm text-sm ml-2" onClick={_ => dispatch(Reset)}>
             {React.string({j|Återställ filter|j})}
           </button>
         | (None, None) => React.null
         }}
      </div>
      {switch (response##allCrops) {
       | Some(crops) =>
         Belt.List.(
           crops##nodes
           ->fromArray
           ->keepMap(i => i)
           ->map(Crop.make)
           ->keep(({season}) =>
               season->Belt.List.some(s => s === Crop.InSeason.In)
             )
           ->keep(crop =>
               Js.String.(
                 switch (state.search) {
                 | None => true
                 | Some(search) =>
                   crop.name |> toLowerCase |> includes(search |> toLowerCase)
                 }
               )
             )
           ->keep(crop =>
               switch (state.category) {
               | None => true
               | Some(cat) => crop.category === cat
               }
             )
           ->keep(crop =>
               switch (state.season, crop.season) {
               | (Some(season), seasonList) =>
                 switch (seasonList->Belt.List.get(season)) {
                 | Some(In) => true
                 | Some(Out)
                 | None => false
                 }
               | (None, _) => true
               }
             )
           ->sort((a, b) =>
               Js.String.localeCompare(b.name, a.name)->int_of_float
             )
           ->map(crop =>
               <Year crop key={crop.id} selectedSeason={state.season} />
             )
           ->Belt.List.toArray
           ->React.array
         )
       | None => <div> {React.string("No crops")} </div>
       }}
    </Layout>
  };
};
