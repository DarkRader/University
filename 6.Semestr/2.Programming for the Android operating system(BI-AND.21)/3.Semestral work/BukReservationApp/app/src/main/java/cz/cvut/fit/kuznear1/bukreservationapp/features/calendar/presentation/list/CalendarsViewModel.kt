package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.list

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.CalendarRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class CalendarsViewModel(
    private val calendarRepository: CalendarRepository
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(CalendarsScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val calendarsResults = calendarRepository.getCalendars()
            _screenStateStream.update {
                it.copy(calendars = calendarsResults.calendars)
            }
        }
    }

//    fun findCalendarTypeByID(id: String): String {
//        val calendar = _screenStateStream.value.calendars.find { it.calendar_id == id }
//        return calendar!!.reservation_type
//    }

    fun updateCalendars() {
        viewModelScope.launch {
            val calendars = calendarRepository.getAllCalendar()
            _screenStateStream.update { it.copy(calendars = calendars)}
        }
    }
}

data class CalendarsScreenState(
    val calendars: List<Calendar> = emptyList()
)