[@react.component]
let make = (~children, ~isSelected, ~onClick) => {
  <button
    className={Cn.make([
      "px-3 py-1 text-sm bg-gray-300 text-gray-700 text-sm
          rounded-full mr-2",
      "bg-green-200
            text-green-700"->Cn.ifTrue(isSelected),
    ])}
    onClick>
    children
  </button>;
};
