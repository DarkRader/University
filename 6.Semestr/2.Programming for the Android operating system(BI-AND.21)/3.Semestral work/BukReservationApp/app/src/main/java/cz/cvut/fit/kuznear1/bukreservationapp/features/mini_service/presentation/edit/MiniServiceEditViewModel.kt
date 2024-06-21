package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.edit

import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.MiniServiceRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.ProfileRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class MiniServiceEditViewModel(
    private val savedStateHandle: SavedStateHandle,
    private val miniServiceRepository: MiniServiceRepository,
    private val profileRepository: ProfileRepository
) : ViewModel() {

    private val id: String
        get() = savedStateHandle[Screens.MiniServiceDetailScreen.ID_KEY] ?: error("Mini Service id is missing")

    private val _screenStateStream = MutableStateFlow(MiniServiceEditScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val miniService = miniServiceRepository.getMiniService(id)
            val username = profileRepository.getUser()
            _screenStateStream.update {
                it.copy(
                    editedMiniService = MiniServiceRequest(miniService!!.name, miniService.service_alias),
                    username = username
                )
            }
        }
    }

    fun onSubmitClick(editMiniService: MiniServiceRequest) {
        viewModelScope.launch {
            val username = _screenStateStream.value.username

            if (username != null) {
                miniServiceRepository.editMiniService(id, username, editMiniService)
            }
        }
    }

}

data class MiniServiceEditScreenState(
    val editedMiniService: MiniServiceRequest? = null,
    val username: String? = null
)