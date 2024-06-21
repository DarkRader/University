package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.edit

import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.CalendarRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.ProfileRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class CalendarEditViewModel(
    private val savedStateHandle: SavedStateHandle,
    private val calendarRepository: CalendarRepository,
    private val profileRepository: ProfileRepository
) : ViewModel() {

    private val id: String
        get() = savedStateHandle[Screens.MiniServiceDetailScreen.ID_KEY] ?: error("Calendar id is missing")

    private val _screenStateStream = MutableStateFlow(CalendarEditScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val calendar = calendarRepository.getCalendar(id)
            val collisions = calendarRepository.getAllCalendar()
            val username = profileRepository.getUser()
            _screenStateStream.update {
                it.copy(
                    editedCalendar = calendar,
                    collisionsCalendar = collisions,
                    username = username
                )
            }
        }
    }

    fun onSubmitClick(calendar: Calendar) {
        viewModelScope.launch {
            val username = _screenStateStream.value.username

            if(username != null) {
                calendarRepository.editCalendar(id, username, calendar)
            }
        }
    }

    fun updateCalendar(calendar: Calendar) {
        _screenStateStream.update {
            it.copy(editedCalendar = calendar)
        }
    }

}

data class CalendarEditScreenState(
    val editedCalendar: Calendar? = null,
    val username: String? = null,
    val collisionsCalendar: List<Calendar> = emptyList()
)