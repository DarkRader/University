package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.detail

import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.MiniServiceRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniService
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.ProfileRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class MiniServiceDetailViewModel(
    private val savedStateHandle: SavedStateHandle,
    private val miniServiceRepository: MiniServiceRepository,
    private val profileRepository: ProfileRepository
) : ViewModel() {

    private val id: String
        get() = savedStateHandle[Screens.MiniServiceDetailScreen.ID_KEY] ?: error("Mini Service id is missing")

    private val _screenStateStream = MutableStateFlow(MiniServiceDetailScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val miniService = miniServiceRepository.getMiniService(id)
            val username = profileRepository.getUser()
            _screenStateStream.update { it.copy(miniService = miniService,
                 username = username) }
        }
    }

    fun deleteMiniService() {
        viewModelScope.launch {
            val screenState = screenStateStream.value
            if(screenState.username != null) {
                miniServiceRepository.deleteMiniService(
                    screenState.miniService!!.uuid,
                    screenState.username
                )
            }
        }
    }

    fun updateMiniService() {
        viewModelScope.launch {
            _screenStateStream.update {
                val miniService = miniServiceRepository.getMiniService(id)
                it.copy(miniService = miniService)
            }
        }
    }
}

data class MiniServiceDetailScreenState(
    val miniService: MiniService? = null,
    val username: String? = null
)