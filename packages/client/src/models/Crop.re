module Category = {
  type t = [ | `FRUIT | `VEGETABLE];
};

module InSeason = {
  type t =
    | In
    | Out;
};

module Season = {
  let make = season => {
    switch (season) {
    | None => []
    | Some(season) =>
      switch (season->Belt.Array.length) {
      | 12 => Belt.List.make(12, InSeason.In)
      | _ =>
        Belt.List.make(12, InSeason.Out)
        ->Belt.List.mapWithIndex((index, _) =>
            switch (
              index,
              season
              ->Belt.List.fromArray
              ->Belt.List.keepMap(m => m)
              ->Belt.List.map(Month.toInt)
              ->Belt.List.some(m => m - 1 === index),
            ) {
            | (_, true) => InSeason.In
            | _ => Out
            }
          )
      }
    };
  };
};

type t = {
  id: string,
  name: string,
  season: list(InSeason.t),
  category: Category.t,
};

let make = crop => {
  id: Slug.make(crop##name),
  name: crop##name,
  season: Season.make(crop##season),
  category: crop##category,
};
