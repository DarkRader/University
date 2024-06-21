package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.detail

import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.CalendarRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.ProfileRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

@Suppress
class CalendarDetailViewModel(
    private val savedStateHandle: SavedStateHandle,
    private val calendarRepository: CalendarRepository,
    private val profileRepository: ProfileRepository
) : ViewModel() {

    private val id: String
        get() = savedStateHandle[Screens.CalendarDetailScreen.ID_KEY] ?: error("Calendar id is missing")

    private val _screenStateStream = MutableStateFlow(CalendarDetailScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val calendars = calendarRepository.getAllCalendar()
            val calendar = calendars.find { it.calendar_id == id }
            val username = profileRepository.getUser()
            _screenStateStream.update {
                it.copy(
                    calendar = calendar,
                    calendars = calendars,
                    username = username
                )
            }
        }
    }

    fun findCalendarTypeByID(id: String): String {
        val calendar = _screenStateStream.value.calendars.find { it.calendar_id == id }
        return calendar!!.reservation_type
    }

    fun deleteCalendar() {
        viewModelScope.launch {
            val screenState = screenStateStream.value
            if(screenState.username != null) {
                calendarRepository.deleteCalendar(
                    screenState.calendar!!.calendar_id,
                    screenState.username
                )
            }
        }
    }

    fun updateCalendar() {
        viewModelScope.launch {
            val calendars = calendarRepository.getAllCalendar()
            val calendar = calendars.find { it.calendar_id == id }
            val username = profileRepository.getUser()
            _screenStateStream.update {
                it.copy(
                    calendar = calendar,
                    calendars = calendars,
                    username = username
                )
            }
        }
    }

}

data class CalendarDetailScreenState(
    val calendar: Calendar? = null,
    val calendars: List<Calendar> = emptyList(),
    val username: String? = null
)