// syncronously add
export function addSensorState(state, { sensorKey, sensorData }) {
  state.data.push({
    id: sensorKey,
    temperature: sensorData.temperature,
    pulse: sensorData.pulse,
    spo2: sensorData.spo2,
    timestamp: sensorData.timestamp
  });
  state.count++
}

export function updateSensorState(state, { sensorKey, sensorData }) {
  const sensorEntry = state.data.find(element => element.id == sensorKey)
  if (sensorEntry) {
    sensorEntry.temperature = sensorData.temperature
    sensorEntry.pulse = sensorData.pulse
    sensorEntry.spo2 = sensorData.spo2
    sensorEntry.timestamp = sensorData.timestamp
  }
  state.count++
}


