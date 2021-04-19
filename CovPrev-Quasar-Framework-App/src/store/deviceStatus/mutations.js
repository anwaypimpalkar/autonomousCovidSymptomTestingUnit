export function addDeviceStatus(state, { deviceStatusKey, deviceStatusData }) {
    state.status.id = deviceStatusKey
    state.status.timestamp = deviceStatusData
}


export function updateDeviceStatus(state, { deviceStatusKey, deviceStatusData }) {
    state.status.id = deviceStatusKey
    state.status.timestamp = deviceStatusData
}

export function currentTime(state, { time }) {
    state.status.currentTime = time
}