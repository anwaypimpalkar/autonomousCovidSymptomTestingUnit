export function fbReadData({ commit }, db) {
  let sensorIDData = db.ref("sensorData");

  sensorIDData.on("child_added", snapshot => {
    let sensorKey = snapshot.key;
    let sensorData = snapshot.val();
    commit("addSensorState", { sensorKey, sensorData });
  });

  sensorIDData.on("child_changed", snapshot => {
    let sensorKey = snapshot.key;
    let sensorData = snapshot.val();
    commit("updateSensorState", { sensorKey, sensorData });
  });
}

//  dispatch - action
//   commit - mutation
