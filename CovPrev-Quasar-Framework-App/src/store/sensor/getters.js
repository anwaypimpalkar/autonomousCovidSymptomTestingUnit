import sensor from ".";

export function getTemp(state) {
    const t = state.data.map((s, index) => {
        return s.temperature
    })
    return t.slice(-10)
}

export function getPulse(state) {
    const t = state.data.map((s, index) => {
        return s.pulse
    })
    return t.slice(-10)
}

export function getSpO2(state) {
    const t = state.data.map((s, index) => {
        return s.spo2
    })
    return t.slice(-10)
}

export function getID(state) {
    const t = state.data.map((s, index) => {
        return s.id
    })
    return t.slice(-10)
}

export function getDataCount(state) {
    return state.count
}
