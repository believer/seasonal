open Jest;
open Expect;

test("english text", () =>
  expect(Slug.make("Carrot")) |> toEqual("carrot")
);

test({j|text with å|j}, () =>
  expect(Slug.make({j|Brysselkål|j})) |> toEqual("brysselkal")
);

test({j|text with ä|j}, () =>
  expect(Slug.make({j|Jordärtskocka|j})) |> toEqual("jordartskocka")
);

test({j|text with ö|j}, () =>
  expect(Slug.make({j|Gul lök|j})) |> toEqual("gul-lok")
);
