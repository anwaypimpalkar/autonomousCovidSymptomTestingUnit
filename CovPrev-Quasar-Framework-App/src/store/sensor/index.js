import state from './state'
import * as getters from './getters'
import * as mutations from './mutations'
import * as actions from './actions'
import { firebaseDb } from 'boot/firebase'

export default {
  namespaced: true,
  state,
  getters,
  mutations,
  actions
}
