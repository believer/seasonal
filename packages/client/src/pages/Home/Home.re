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

  <div className="grid grid-template-main mt-24">
    <div className="grid-column-main">
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
        <button
          className={Cn.make([
            "px-3 py-1 text-sm bg-gray-300 text-gray-700 text-sm
          rounded-full mr-2",
            switch (state.category) {
            | Some(Fruit) => "bg-green-200 text-green-700"
            | Some(Vegetable)
            | None => ""
            },
          ])}
          onClick={_ => dispatch(Category(Some(Fruit)))}>
          {React.string("Frukt")}
        </button>
        <button
          className={Cn.make([
            "px-3 py-1 text-sm bg-gray-300 text-gray-700 text-sm
          rounded-full mr-2",
            switch (state.category) {
            | Some(Vegetable) => "bg-green-200 text-green-700"
            | Some(Fruit)
            | None => ""
            },
          ])}
          onClick={_ => dispatch(Category(Some(Vegetable)))}>
          {React.string({j|Grönsaker|j})}
        </button>
        <button
          className={Cn.make([
            "px-3 py-1 text-sm bg-gray-300 text-gray-700 text-sm
          rounded-full",
            switch (state.season) {
            | Some(_) => "bg-green-200 text-green-700"
            | None => ""
            },
          ])}
          onClick={_ => dispatch(InSeason)}>
          {React.string({j|I säsong|j})}
        </button>
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
      Belt.List.(
        Crops.list
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
    </div>
  </div>;
};
