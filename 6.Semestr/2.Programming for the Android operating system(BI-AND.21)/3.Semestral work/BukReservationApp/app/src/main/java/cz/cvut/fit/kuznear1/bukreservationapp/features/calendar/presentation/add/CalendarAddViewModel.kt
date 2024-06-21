package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.add

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.CalendarRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api.ApiCalendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.CreateDefaultCalendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.ProfileRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class CalendarAddViewModel(
    private val calendarRepository: CalendarRepository,
    private val profileRepository: ProfileRepository
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(CalendarAddScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val collisions = calendarRepository.getAllCalendar()
            val username = profileRepository.getUser()
            _screenStateStream.update {
                it.copy(
                    collisionsCalendar = collisions,
                    username = username
                )
            }
        }
    }

    fun onSubmitClick(newCalendar: Calendar) {
        viewModelScope.launch {
            val username = _screenStateStream.value.username
            if(username != null) {
                calendarRepository.createCalendar(username, newCalendar)
            }
        }
    }

}

data class CalendarAddScreenState(
    val newCalendar: Calendar = CreateDefaultCalendar(),
    val username: String? = null,
    val collisionsCalendar: List<Calendar> = emptyList()
)