package cz.cvut.kuznear1.dogapp

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class MainViewModel : ViewModel() {

    private val _screenStateStream = MutableStateFlow(MainScreenState())
    val screenStateStream get() = _screenStateStream.asStateFlow()

    fun onGetDogFactsClick() {
        viewModelScope.launch {
            val limit = _screenStateStream.value.limit.toInt()
            val dogFacts = DogDataSource.getDogFacts(limit).data.map {
                it.attributes.fact
            }
            _screenStateStream.update { state ->
                state.copy(dogFacts = dogFacts)
            }
        }
    }

    fun onLimitTextChange(limit: String) {
        _screenStateStream.update { state ->
            state.copy(limit = limit)
        }
    }
}

data class MainScreenState(
    val dogFacts: List<String> = emptyList(),
    val limit: String = "1",
)