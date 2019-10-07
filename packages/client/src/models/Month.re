type t = [
  | `Jan
  | `Feb
  | `Mar
  | `Apr
  | `May
  | `Jun
  | `Jul
  | `Aug
  | `Sep
  | `Oct
  | `Nov
  | `Dec
];

let toInt =
  fun
  | `Jan => 1
  | `Feb => 2
  | `Mar => 3
  | `Apr => 4
  | `May => 5
  | `Jun => 6
  | `Jul => 7
  | `Aug => 8
  | `Sep => 9
  | `Oct => 10
  | `Nov => 11
  | `Dec => 12;

let fromInt =
  fun
  | 0 => `Jan
  | 1 => `Feb
  | 2 => `Mar
  | 3 => `Apr
  | 4 => `May
  | 5 => `Jun
  | 6 => `Jul
  | 7 => `Aug
  | 8 => `Sep
  | 9 => `Oct
  | 10 => `Nov
  | _ => `Dec;
