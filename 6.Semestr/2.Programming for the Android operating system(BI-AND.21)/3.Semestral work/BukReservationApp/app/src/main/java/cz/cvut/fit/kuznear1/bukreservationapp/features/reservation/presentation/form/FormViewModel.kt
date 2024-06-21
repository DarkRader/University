package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.form

import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.CalendarRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.CreateDefaultCalendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.ProfileRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.ReservationRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.CreateDefaultEvent
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.CreateEvent
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.Reservation
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class FormViewModel(
    private val savedStateHandle: SavedStateHandle,
    private val reservationRepository: ReservationRepository,
    private val calendarRepository: CalendarRepository,
    private val profileRepository: ProfileRepository
) : ViewModel() {

    private val alias: String
        get() = savedStateHandle[Screens.FormScreen.ALIAS_KEY] ?: error("Form alias is missing")

    private val _screenStateStream = MutableStateFlow(FormScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val username = profileRepository.getUser()
            val calendars = calendarRepository.getAllCalendar()
            val reservationTypes = calendars.filter { it.service_alias == alias }
            _screenStateStream.update {
                it.copy(username = username, reservationTypes = reservationTypes)
            }
        }
    }

    fun onSubmitClick(newEvent: CreateEvent) {
        viewModelScope.launch {
            val username = _screenStateStream.value.username
            if(username != null) {
                val updatedEvent = newEvent.copy(username = username)
                val result = reservationRepository.postEvent(updatedEvent)
                if(!result.isSuccess) {
                    _screenStateStream.update {
                        it.copy(notLogin = true)
                    }
                } else {
                    if(result.message != "" && result.message != "Could not create event.") {
                        _screenStateStream.update {
                            it.copy(warningMessage = result.message)
                        }
                    } else {
                        _screenStateStream.update {
                            it.copy(warningMessage = "")
                        }
                    }
                    if(result.message != "Could not create event.") {
                        reservationRepository.insertReservation(
                            Reservation(
                                typeReservation = newEvent.reservation_type,
                                reservationFrom = newEvent.start_datetime,
                                reservationTo = newEvent.end_datetime
                            )
                        )
                    }
                }
            }
        }
    }

    fun whenTypeChosen(type: String) {
        viewModelScope.launch {
            val calendar = _screenStateStream.value.reservationTypes.find { it.reservation_type == type }
            if(calendar != null) {
                _screenStateStream.update {
                    it.copy(chosenType = calendar)
                }
            }
        }
    }

    fun onReceivedCode(code: String) {
        viewModelScope.launch {
            val username = profileRepository.authorized(code)
            _screenStateStream.update {
                it.copy(username = username)
            }
        }
    }

}

data class FormScreenState(
    val event: CreateEvent = CreateDefaultEvent(),
    val reservationTypes: List<Calendar> = emptyList(),
    val chosenType: Calendar = CreateDefaultCalendar(),
    val username: String? = null,
    val notLogin: Boolean = false,
    val warningMessage: String = ""
)