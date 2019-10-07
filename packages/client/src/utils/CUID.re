type t = string;

[@bs.module] external make: unit => t = "cuid";

let toString = id => id;
