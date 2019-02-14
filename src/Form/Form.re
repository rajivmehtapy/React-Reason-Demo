/* State declaration */
type state = {
  firstName: string,
  lastName: string,
};

/* Action declaration */
type action =
  | Change(string, string);

let component = ReasonReact.reducerComponent("Form");

let make = _children => {
  ...component,
  initialState: () => {firstName: "", lastName: ""},
  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Change(field, v) => 
      switch (field) {
      | "firstName" => ReasonReact.Update({...state, firstName: v })
      | "lastName" => ReasonReact.Update({...state, lastName: v })
      };
    },

  render: self =>
    <div className="app">
      <div className="items">
        <form className="form">
          <input
            className="mb-5 text-box" placeholder="first name"
            value={self.state.firstName}
            onChange={e => {
              let v = ReactEvent.Form.target(e)##value;
              self.send(Change("firstName", v))
            }}
          />
          <input
            className="mb-5 text-box" placeholder="last name"
            value={self.state.lastName}
            onChange=(e => {
              let v = ReactEvent.Form.target(e)##value;
              self.send(Change("lastName", v))
            })
          />
          <button className="mb-5 btn">
            (ReasonReact.string("Submit"))
          </button>
        </form>
        <div>(ReasonReact.string(self.state.firstName))</div>
        <div>(ReasonReact.string(self.state.lastName))</div>
      </div>
    </div>,
};
