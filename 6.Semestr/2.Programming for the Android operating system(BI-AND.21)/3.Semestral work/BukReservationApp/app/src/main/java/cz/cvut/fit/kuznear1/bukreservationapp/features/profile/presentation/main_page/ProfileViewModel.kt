package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.presentation.main_page

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.ProfileRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class ProfileViewModel(
    private val profileRepository: ProfileRepository
) : ViewModel() {
    private val _screenStateStream = MutableStateFlow(ProfileScreensState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val username = profileRepository.getUser()
            if(username != null) {
                _screenStateStream.update {
                    it.copy(username = username)
                }
            }
        }
    }

    fun onReceivedCode(code: String) {
        viewModelScope.launch {
            val username = profileRepository.authorized(code)
            _screenStateStream.update {
                it.copy(username = username)
            }
        }
    }
}

data class ProfileScreensState(
    val username: String? = null
)