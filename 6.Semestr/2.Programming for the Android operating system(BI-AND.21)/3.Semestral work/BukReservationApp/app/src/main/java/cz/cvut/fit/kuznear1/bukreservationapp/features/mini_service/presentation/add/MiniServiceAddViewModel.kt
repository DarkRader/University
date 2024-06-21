package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.add

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.MiniServiceRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.ProfileRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class MiniServiceAddViewModel(
    private val miniServicesRepository: MiniServiceRepository,
    private val profileRepository: ProfileRepository
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(MiniServiceAddScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val username = profileRepository.getUser()
            _screenStateStream.update {
                it.copy(username = username)
            }
        }
    }

    fun onSubmitClick(newMiniService: MiniServiceRequest) {
        viewModelScope.launch {
            val username = _screenStateStream.value.username

            if(username != null) {
                miniServicesRepository.createMiniService(username, newMiniService)
            }
        }
    }

}

data class MiniServiceAddScreenState(
    val newMiniService: MiniServiceRequest? = null,
    val username: String? = null
)