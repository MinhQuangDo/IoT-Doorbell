var myParticleAccessToken = "1a357255a7ae96b19fddcb4c1a0eda21a5b5ac5e"
var myDeviceId = "500020000751373238323937"
var topic = "IoTDoorbell"

function newGarageEvent(objectContainingData) {
      let data = JSON.parse(objectContainingData.data)
      doorbell.doorPowered = data.doorState;

      // publish the state to any listeners
      doorbell.stateChange()
    }

const doorStatus = {
    open: "Open",
    close: "Closed",
  }

//doorbell object - saving all information
  var doorbell = {
      doorPowered: doorStatus.close,

      stateChangeListener: null,

      particle: null,

      //funcion represents door button hit
      setDoorPowered: function() {
        //change the door state based on the current state
        if (this.doorPowered == doorStatus.open) {
          this.doorPowered = doorStatus.close
        }
        else if (this.doorPowered == doorStatus.close) {
          this.doorPowered = doorStatus.open
        }

        var functionData = {
          deviceId:myDeviceId,
          name: "doorButtonPress",
          argument: "",
          auth: myParticleAccessToken
       }

          // Include functions to provide details about the process.
        function onSuccess(e) { console.log("setDoorPowered call success") }
        function onFailure(e) { console.log("setDoorPowered call failed")
                              console.dir(e) }
        particle.callFunction(functionData).then(onSuccess,onFailure)
      },

      setStateChangeListener: function(aListener) {
        this.stateChangeListener = aListener
      },

      stateChange: function() {
        if (this.stateChangeListener) {
          var state = { doorPowered: this.doorPowered};
        this.stateChangeListener(state);
        }
      },

      setup: function() {
      // Create a particle object
        particle = new Particle();

        // Get ready to subscribe to the event stream
        function onSuccess(stream) {
          console.log("getEventStream success")
          stream.on('event', newGarageEvent)

          var functionData = {
            deviceId: myDeviceId,
            name: "publishState",
            argument: "",
            auth: myParticleAccessToken
          }
          function onSuccess2(e) { console.log("publish call success") }
          function onFailure2(e) { console.log("publish call failed")
                                console.dir(e) }

          particle.callFunction(functionData).then(onSuccess2, onFailure2);
        }
        function onFailure(e) { console.log("getEventStream call failed")
                                console.dir(e) }
        // Subscribe to the stream
        particle.getEventStream( { name: topic, auth: myParticleAccessToken, deviceId: 'mine' }).then(onSuccess, onFailure)
    }
  }
