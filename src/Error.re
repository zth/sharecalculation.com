[@react.component]
let make = () =>
  <div>
    <Box>
      <h2> {React.string("Oops, error!")} </h2>
      <ExplanatoryText
        text="Something went wrong here. Maybe the link you used is broken or old?"
      />
    </Box>
  </div>;