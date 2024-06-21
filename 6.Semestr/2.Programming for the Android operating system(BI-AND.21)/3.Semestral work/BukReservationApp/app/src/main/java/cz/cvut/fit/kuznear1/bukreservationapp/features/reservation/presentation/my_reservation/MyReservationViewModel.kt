package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.my_reservation

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.ReservationRepository
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.Reservation
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class MyReservationViewModel(
    private val reservationRepository: ReservationRepository,
): ViewModel() {
    private val _screenStateStream = MutableStateFlow(MyReservationScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val reservations = reservationRepository.getAllReservations()
            _screenStateStream.update {
                it.copy(myReservations = reservations)
            }
        }
    }
}

data class MyReservationScreenState(
    val myReservations: List<Reservation> = emptyList(),
)