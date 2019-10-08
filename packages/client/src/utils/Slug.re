let make = text =>
  Js.String.(
    text
    |> toLowerCase
    |> replaceByRe([%re "/[åä]/g"], "a")
    |> replaceByRe([%re "/ö/g"], "o")
    |> replaceByRe([%re "/\\s/g"], "-")
  );
