module H1 = {
  [@react.component]
  let make = (~children, ~className=?) => {
    <h1 className={Cn.make(["text-2xl font-semibold", className->Cn.unpack])}>
      children
    </h1>;
  };
};

module H2 = {
  [@react.component]
  let make = (~children, ~className=?) => {
    <h2 className={Cn.make([className->Cn.unpack])}> children </h2>;
  };
};

module H3 = {
  [@react.component]
  let make = (~children, ~className=?) => {
    <h3 className={Cn.make([className->Cn.unpack])}> children </h3>;
  };
};
