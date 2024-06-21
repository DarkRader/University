package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.detail

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniService
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.DetailTopBar
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.TextHeaderStyle
import org.koin.androidx.compose.koinViewModel

@Composable
fun MiniServiceDetailScreen(
    navController: NavController,
    viewModel: MiniServiceDetailViewModel = koinViewModel()
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    LaunchedEffect(Unit) {
        viewModel.updateMiniService()
    }

    MiniServiceDetailScreen(
        screenState = screenState,
        onEditClick = { miniService ->
            navController.navigate(Screens.MiniServiceEditScreen.route + "/${miniService.uuid}")
        },
        onDeleteClick = viewModel::deleteMiniService,
        onNavigateBackClick = { navController.navigate(Screens.MiniServicesScreen.route) },
    )
}

@Composable
private fun MiniServiceDetailScreen(
    screenState: MiniServiceDetailScreenState,
    onEditClick: (MiniService) -> Unit,
    onDeleteClick: () -> Unit,
    onNavigateBackClick: () -> Unit,
) {
    screenState.miniService?.let { miniService ->
        Scaffold(
            topBar = {
                DetailTopBar(
                    headerText = miniService.name,
                    onEditClick = { onEditClick(miniService) },
                    onDeleteClick = onDeleteClick,
                    onNavigateBackClick = onNavigateBackClick,
                )
            },
            containerColor = MaterialTheme.colorScheme.primaryContainer
        ) {
            Box(modifier = Modifier.padding(it)) {
                MiniServiceDetail(miniService = miniService)
            }
        }
    }
}

@Composable
private fun MiniServiceDetail(miniService: MiniService) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState())
    ) {
        Card(
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp),
            elevation = CardDefaults.cardElevation(2.dp),
            shape = RoundedCornerShape(16.dp),
            colors = CardDefaults.cardColors(containerColor = MaterialTheme.colorScheme.secondaryContainer)
        ) {
            Column(
                modifier = Modifier
                    .fillMaxWidth(fraction = 2 / 3f)
                    .padding(horizontal = 16.dp, vertical = 16.dp),
                verticalArrangement = Arrangement.spacedBy(14.dp),
            ) {
                TextHeaderStyle(miniService.name, "Name")
                TextHeaderStyle(miniService.service_alias, "Server alias")
            }
        }
    }
}