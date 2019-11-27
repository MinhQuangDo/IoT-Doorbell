//program that controls and updates UI along with doorbell model

//variables representing elements on the screen
var doorStatusLabel
var doorButton
var lockStatusLabel
var lockButton

//when the door button is clicked
function doorClicked(event) {
  doorbell.setDoorPowered()
}

//when the lock button is clicked
function lockClicked(event) {
  doorbell.setLock()
}

function loadingPage(value) {
  document.getElementById("allControls").hidden = value;
}

//when the garage model is updated
function stateUpdate(newState) {
  loadingPage(false);
  doorStatusLabel.innerText = newState.doorPowered
  if (newState.doorPowered == "Open") {
    lockButton.disabled = true
  } else {
    lockButton.disabled = false
  }
  if (newState.locked) {
    lockStatusLabel.innerText = "Locked"
    doorButton.disabled = true;
  } else {
    lockStatusLabel.innerText = "Unlocked"
    doorButton.disabled = false;
  }
}

window.addEventListener("load", function(event) {
  doorButton = document.getElementById("doorButton")
  doorStatusLabel = document.getElementById("doorStatus")
  lockButton = document.getElementById("lockButton")
  lockStatusLabel = document.getElementById("lockStatus")
  doorButton.addEventListener("click", doorClicked)
  lockButton.addEventListener("click", lockClicked)


  loadingPage(true)

  doorbell.setStateChangeListener(stateUpdate)
  doorbell.setup()

})
