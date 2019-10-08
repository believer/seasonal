let list =
  Crop.[
    make(
      ~name="Avokado",
      ~season=Months([`Oct, `Nov, `Dec]),
      ~category=Fruit,
    ),
    make(
      ~name="Citron",
      ~season=Months([`Jan, `Feb, `Mar, `Dec]),
      ~category=Fruit,
    ),
    make(~name="Potatis", ~season=AllYear, ~category=Vegetable),
    make(
      ~name={j|Rödlök|j},
      ~season=
        Months([`Jan, `Feb, `Mar, `Jun, `Jul, `Aug, `Sep, `Oct, `Nov, `Dec]),
      ~category=Vegetable,
    ),
    make(
      ~name={j|Gul lök|j},
      ~season=
        Months([
          `Jan,
          `Feb,
          `Mar,
          `Apr,
          `Jun,
          `Jul,
          `Aug,
          `Sep,
          `Oct,
          `Nov,
          `Dec,
        ]),
      ~category=Vegetable,
    ),
    make(
      ~name={j|Gurka|j},
      ~season=Months([`Apr, `May, `Jun, `Jul, `Aug, `Sep, `Oct]),
      ~category=Vegetable,
    ),
    make(
      ~name={j|Morot|j},
      ~season=
        Months([
          `Jan,
          `Feb,
          `Mar,
          `Apr,
          `Jun,
          `Jul,
          `Aug,
          `Sep,
          `Oct,
          `Nov,
          `Dec,
        ]),
      ~category=Vegetable,
    ),
  ];

let find = cropId =>
  list->Belt.List.keep(({id}) => id === cropId)->Belt.List.get(0);
