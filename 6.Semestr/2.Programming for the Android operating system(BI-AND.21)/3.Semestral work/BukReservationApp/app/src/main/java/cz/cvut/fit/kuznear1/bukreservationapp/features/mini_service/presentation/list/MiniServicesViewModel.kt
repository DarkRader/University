package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.list

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.MiniServiceRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniService
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class MiniServicesViewModel(
    private val miniServiceRepository: MiniServiceRepository
) : ViewModel() {
    private val _screenStateStream = MutableStateFlow(MiniServicesScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val miniServicesResults = miniServiceRepository.getMiniServices()
            _screenStateStream.update { it.copy(miniServices = miniServicesResults.miniServices) }
        }
    }

    fun updateMiniServices() {
        viewModelScope.launch {
            val miniServices = miniServiceRepository.getAllMiniServices()
            _screenStateStream.update { it.copy(miniServices = miniServices) }
        }
    }

}

data class MiniServicesScreenState(
    val miniServices: List<MiniService> = emptyList()
)