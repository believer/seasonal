type format = [ | `Row | `Grid];

[@react.component]
let make = (~format: format=`Row, ~season, ~selectedSeason=None) => {
  let className =
    switch (format) {
    | `Row => "grid grid-template-12 grid-column-gap-1/8 md:flex items-center"
    | `Grid => "grid grid-template-12 grid-column-gap-1/8"
    };

  <div className>
    {season
     ->Belt.List.mapWithIndex((i, s) =>
         <div
           className={Cn.make([
             "h-5 rounded-sm",
             switch (format) {
             | `Row => "md:w-10"
             | `Grid => ""
             },
             switch (selectedSeason, s) {
             | (Some(m), Crop.InSeason.In) when m === i => "bg-orange-400"
             | (_, In) => "bg-green-400"
             | (_, Out) => "bg-gray-400"
             },
           ])}
           key={i->string_of_int}
         />
       )
     ->Belt.List.toArray
     ->React.array}
  </div>;
};
