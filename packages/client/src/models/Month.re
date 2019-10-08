type t = [
  | `JAN
  | `FEB
  | `MAR
  | `APR
  | `MAY
  | `JUN
  | `JUL
  | `AUG
  | `SEP
  | `OCT
  | `NOV
  | `DEC
];

let toInt =
  fun
  | `JAN => 1
  | `FEB => 2
  | `MAR => 3
  | `APR => 4
  | `MAY => 5
  | `JUN => 6
  | `JUL => 7
  | `AUG => 8
  | `SEP => 9
  | `OCT => 10
  | `NOV => 11
  | `DEC => 12;

let fromInt =
  fun
  | 0 => `JAN
  | 1 => `FEB
  | 2 => `MAR
  | 3 => `APR
  | 4 => `MAY
  | 5 => `JUN
  | 6 => `JUL
  | 7 => `AUG
  | 8 => `SEP
  | 9 => `OCT
  | 10 => `NOV
  | _ => `DEC;
