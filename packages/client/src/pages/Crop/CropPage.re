module GetCrop = [%graphql
  {|
  query GetCrop($name: String!) {
    cropByName(name: $name) {
      category
      name
      season
    }
  }
|}
];

module GetCropQuery = ReasonApolloHooks.Query.Make(GetCrop);

[@react.component]
let make = (~name) => {
  let variables = GetCrop.make(~name, ())##variables;
  let (result, _full) = GetCropQuery.use(~variables, ());

  <div>
    {switch (result) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       switch (data##cropByName) {
       | Some(cropByName) =>
         let crop = Crop.make(cropByName);

         <Layout>
           <Router.Link
             className="inline-block mb-4 underline text-green-700"
             to_=Router.Route.HomeRoute>
             {React.string("Tillbaka")}
           </Router.Link>
           <Typography.H1> {React.string(crop.name)} </Typography.H1>
           <div className="mt-4">
             <YearSeason format=`Grid season={crop.season} />
           </div>
         </Layout>;
       | None => <div> {React.string("No crop")} </div>
       }
     | NoData
     | Error(_) => <p> {React.string("Get off my lawn!")} </p>
     }}
  </div>;
};
