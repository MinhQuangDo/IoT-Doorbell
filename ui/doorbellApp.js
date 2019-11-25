//program that controls and updates UI along with garage model

//variables representing elements on the login screen
var loginButton
var createAccountButton

//variables representing elements on the create account screen
var backButton

//variables representing elements on the "Basic" screen
var logOutButton
var doorStatusLabel
var doorButton
var lightStatusLabel
var lightButton
var autoCloseButton

//variables representing elements on the "Advanced" screen
var autoCloseStatusLabel
var autoCloseTimeSlider
var lightBrightnessSlider
var lightOffTimeSlider
var autoCloseTime
var lightBrightness
var lightOffTime

//when the user login successfully, show the control page
function loginClicked(event) {
  document.getElementById("loginPage").hidden = true
  document.getElementById("allControls").hidden = false;
}

//when the user hit create account, show the create account page
function createAccountClicked(event) {
  document.getElementById("loginPage").hidden = true
  document.getElementById("createAccountPage").hidden = false
}

//when the user hit back to get to the login page
function backClicked(event) {
  document.getElementById("loginPage").hidden = false
  document.getElementById("createAccountPage").hidden = true
}

//when the user log out from control page
function logOutClicked(event) {
  document.getElementById("loginPage").hidden = false
  document.getElementById("allControls").hidden = true;
}

//when the door button is clicked
function doorClicked(event) {
  doorbell.setDoorPowered()
}

function loadingPage(value) {
  document.getElementById("allControls").hidden = value;
}

//when the garage model is updated
function stateUpdate(newState) {
  loadingPage(false);
  doorStatusLabel.innerText = newState.doorPowered
}

window.addEventListener("load", function(event) {
  //login page variables
  loginButton = document.getElementById("loginButton")
  createAccountButton = document.getElementById("createAccountButton")

  //back button in create account page
  backButton = document.getElementById("backButton")


  //door and light on/off variables
  logOutButton = document.getElementById("logOutButton")
  doorButton = document.getElementById("doorButton")
  doorStatusLabel = document.getElementById("doorStatus")

  // faultStatusLabel = document.getElementById("faultStatus")

  //login page event handlers
  // loginButton.addEventListener("click", loginClicked)
  // createAccountButton.addEventListener("click", createAccountClicked)

  //back button event handler in create account page
  // backButton.addEventListener("click", backClicked)

  //door and light on/off event handlers
  // logOutButton.addEventListener("click", logOutClicked)
  doorButton.addEventListener("click", doorClicked)


  loadingPage(true)

  doorbell.setStateChangeListener(stateUpdate)
  doorbell.setup()

})
