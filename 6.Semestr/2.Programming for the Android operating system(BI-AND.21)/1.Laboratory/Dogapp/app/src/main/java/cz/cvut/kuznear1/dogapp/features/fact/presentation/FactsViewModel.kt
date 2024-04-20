package cz.cvut.kuznear1.dogapp.features.fact.presentation

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.kuznear1.dogapp.features.fact.data.FactRepository
import cz.cvut.kuznear1.dogapp.features.fact.domain.Fact
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class FactsViewModel(private val factRepository: FactRepository) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(FactsScreenState())
    val screenStateStream get() = _screenStateStream.asStateFlow()

    fun onGetFactsClick() {
        viewModelScope.launch {
            _screenStateStream.update { state -> state.copy(getFactsState = GetFactsState.Loading) }

            val limit = _screenStateStream.value.limit.toInt()
            val getFactsState = try {
                val facts = factRepository.getFacts(limit)
                GetFactsState.Loaded(facts)
            } catch (t: Throwable) {
                GetFactsState.Error(t)
            }
            _screenStateStream.update { state ->
                state.copy(getFactsState = getFactsState)
            }
        }
    }

    fun onLimitTextChange(limit: String) {
        _screenStateStream.update { state ->
            state.copy(limit = limit)
        }
    }
}

data class FactsScreenState(
    val limit: String = "1",
    val getFactsState: GetFactsState = GetFactsState.Loaded(),
)

sealed interface GetFactsState {

    data object Loading : GetFactsState

    data class Loaded(val facts: List<Fact> = emptyList()) : GetFactsState

    data class Error(val throwable: Throwable) : GetFactsState
}