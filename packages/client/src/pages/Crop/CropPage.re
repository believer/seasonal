[@react.component]
let make = (~cropId) => {
  let crop = Crops.find(cropId);

  switch (crop) {
  | None => <div> {React.string("Cannot find crop")} </div>
  | Some(crop) =>
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
    </Layout>
  };
};
