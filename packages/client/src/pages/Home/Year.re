[@react.component]
let make = (~crop: Crop.t, ~selectedSeason) => {
  <Router.Link
    className="flex items-center justify-end mb-4 last:mb-0"
    to_={Router.Route.CropRoute(crop.id)}>
    <div className="mr-4 text-sm text-right text-gray-700">
      {React.string(crop.name)}
    </div>
    <div className="flex items-center">
      {crop.season
       ->Belt.List.mapWithIndex((i, s) =>
           <div
             className={Cn.make([
               "h-5 w-10 mr-1/8 last:mr-0 rounded-sm",
               switch (selectedSeason, s) {
               | (Some(m), Crop.InSeason.In) when m === i => "bg-orange-300"
               | (_, In) => "bg-green-400"
               | (_, Out) => "bg-gray-300"
               },
             ])}
             key={i->string_of_int}
           />
         )
       ->Belt.List.toArray
       ->React.array}
    </div>
  </Router.Link>;
};
