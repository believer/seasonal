[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let route = Router.Route.fromPath(url.path);

  switch (route) {
  | HomeRoute => <HomePage />
  | CropRoute(name) => <CropPage name />
  | NotFoundRoute => <NotFound />
  };
};
