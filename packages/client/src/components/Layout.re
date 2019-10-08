[@react.component]
let make = (~children) => {
  <div className="grid grid-template-main my-10 md:my-24">
    <div className="grid-column-main"> children </div>
  </div>;
};
