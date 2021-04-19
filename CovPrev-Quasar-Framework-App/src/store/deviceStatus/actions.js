
export function fbReadData({ commit }, db) {
    let deviceStatus = db.ref("deviceStatus");

    deviceStatus.on("child_added", snapshot => {
        let deviceStatusKey = snapshot.key;
        let deviceStatusData = snapshot.val();
        commit("addDeviceStatus", { deviceStatusKey, deviceStatusData });
    });


    deviceStatus.on("child_changed", snapshot => {
        let deviceStatusKey = snapshot.key;
        let deviceStatusData = snapshot.val();
        commit("updateDeviceStatus", { deviceStatusKey, deviceStatusData });
    });

}




export function updateTime({ commit }) {

    setInterval(() => {
        commit("currentTime", { time: Math.round((new Date()).getTime() / 1000) })
    }, 1000);

}



