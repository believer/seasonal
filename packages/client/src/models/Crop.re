module Category = {
  type t =
    | Fruit
    | Vegetable;
};

module InSeason = {
  type t =
    | In
    | Out;
};

module Season = {
  type t =
    | AllYear
    | Months(list(Month.t));

  let make = season => {
    switch (season) {
    | AllYear => Belt.List.make(12, InSeason.In)
    | Months(months) =>
      Belt.List.make(12, InSeason.Out)
      ->Belt.List.mapWithIndex((index, _) =>
          switch (
            index,
            months
            ->Belt.List.map(Month.toInt)
            ->Belt.List.some(m => m - 1 === index),
          ) {
          | (_, true) => InSeason.In
          | _ => Out
          }
        )
    };
  };
};

type t = {
  id: string,
  name: string,
  season: list(InSeason.t),
  category: Category.t,
};

let make = (~name, ~season, ~category) => {
  id: Slug.make(name),
  name,
  season: Season.make(season),
  category,
};
