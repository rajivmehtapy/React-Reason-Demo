type route =
  | Search
  | Form;

type state = {
  route: route
};

type action =
  | ChangeRoute(route)
  | PushRoute(string, ReactEvent.Mouse.t);

module type Mapper = {
  let toPage: ReasonReact.Router.url => route;
  let toUrl: route => string;
};

module Mapper: Mapper = {
  let toPage = (url: ReasonReact.Router.url) =>
    switch (url.hash) {
    | "search" => Search
    | _ => Form
    };
  let toUrl = page =>
    switch (page) {
    | Search => "search"
    | _ => "form"
    };
};

let component = ReasonReact.reducerComponent("App");

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  | PushRoute(path, e) => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReact.Router.push(path);
      ReasonReact.NoUpdate;
    }
  };
/* Js.log (url);*/
let make = _children => {
  ...component,
  reducer,
  didMount: self => {
    let watcherID = ReasonReact.Router.watchUrl(url => {
      switch (url.hash) {
        | "search" => self.send(ChangeRoute(Search))
        | _ => self.send(ChangeRoute(Form))
      }
    });
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  initialState: () => {
    route: ReasonReact.Router.dangerouslyGetInitialUrl() 
      |> Mapper.toPage,
  },
  render: self =>
    <div className="app-wrap">
      <div className="tabs">
        <a
          className={self.state.route === Form ? "tab-item active-tab" : "tab-item"}
          onClick={e => self.send(PushRoute("#form", e))}
        >
          (ReasonReact.string("Form"))
        </a>
        <a
          className={self.state.route === Search ? "tab-item active-tab" : "tab-item"}
          onClick={e => self.send(PushRoute("#search", e))}
        >
          (ReasonReact.string("Search"))
        </a>
      </div>
      {
        switch (self.state.route) {
        | Search => <Search />
        | Form => <Form />
        }
      }
    </div>,
};
