[@react.component]
let make = (~crop: Crop.t, ~selectedSeason) => {
  <Router.Link
    className="md:flex items-center justify-end p-2
    hover:bg-gray-300 rounded"
    to_={Router.Route.CropRoute(crop.id)}>
    <div className="my-2 md:my-0 md:mr-4 text-sm md:text-right text-gray-700">
      {React.string(crop.name)}
    </div>
    <YearSeason season={crop.season} selectedSeason />
  </Router.Link>;
};
