[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let route = Router.Route.fromPath(url.path);

  switch (route) {
  | HomeRoute => <HomePage />
  | CropRoute(cropId) => <CropPage cropId />
  | NotFoundRoute => <NotFound />
  };
};
