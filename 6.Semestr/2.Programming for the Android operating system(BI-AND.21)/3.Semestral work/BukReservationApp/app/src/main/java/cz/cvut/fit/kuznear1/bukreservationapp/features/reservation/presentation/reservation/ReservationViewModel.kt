package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.reservation

import androidx.lifecycle.ViewModel
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.ReservationChip
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.ReservationChipDataSource
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update

class ReservationViewModel(

) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(ReservationScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        _screenStateStream.value = ReservationScreenState(
            reservations = ReservationChipDataSource.getAll()
        )
    }

    fun onReservationChipClick(newCurrentReservation: String,
                               newServiceAlias: String) {
        _screenStateStream.update {
            it.copy(
                chosenReservation = newCurrentReservation,
                serviceAlias = newServiceAlias
            )
        }
    }

}

data class ReservationScreenState(
    val reservations: List<ReservationChip> = emptyList(),
    val chosenReservation: String = "Club Room reservation",
    val serviceAlias: String = "klub"
)