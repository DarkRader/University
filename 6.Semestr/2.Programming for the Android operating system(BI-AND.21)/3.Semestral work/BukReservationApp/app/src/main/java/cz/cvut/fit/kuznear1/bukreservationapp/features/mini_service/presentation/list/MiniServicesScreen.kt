package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.list

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.bukreservationapp.R
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.ListTopBar
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniService
import org.koin.androidx.compose.koinViewModel

@Composable
fun MiniServicesScreen(
    navController: NavController,
    viewModel: MiniServicesViewModel = koinViewModel()
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    LaunchedEffect(Unit) {
        viewModel.updateMiniServices()
    }

    MiniServicesScreen(
        screenState = screenState,

        onNavigateBackClick = { navController.navigate(Screens.ProfileScreen.route) },
        onAddClick = { navController.navigate((Screens.MiniServiceAddScreen.route)) },
        onMiniServiceClick = { miniService ->
            navController.navigate(Screens.MiniServiceDetailScreen.route + "/${miniService.uuid}")
        }
    )
}

@Composable
private fun MiniServicesScreen(
    screenState: MiniServicesScreenState,
    onNavigateBackClick: () -> Unit,
    onAddClick: () -> Unit,
    onMiniServiceClick: (MiniService) -> Unit,
) {
    Scaffold(
        topBar = {
            ListTopBar(
                headerText = "Mini Services",
                onNavigateBackClick = onNavigateBackClick,
                onAddClick = onAddClick,
            )
        },
        containerColor = MaterialTheme.colorScheme.primaryContainer
    ) { innerPadding ->
        LazyColumn(
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding),
            contentPadding = PaddingValues(8.dp),
            verticalArrangement = Arrangement.spacedBy(8.dp)
        ) {
            items(screenState.miniServices, key = { it.uuid }) { miniServices ->
                MiniServiceCard(
                    miniServices = miniServices,
                    onClick = { onMiniServiceClick(miniServices) }
                )
            }
        }
    }
}

@Composable
private fun MiniServiceCard(
    miniServices: MiniService,
    onClick: () -> Unit,
) {
    Card(
        modifier = Modifier.clickable(onClick = onClick),
        elevation = CardDefaults.cardElevation(2.dp),
        shape = RoundedCornerShape(16.dp),
        colors = CardDefaults.cardColors(containerColor = MaterialTheme.colorScheme.secondaryContainer)
    ) {
        MiniServiceItem(
            miniServices = miniServices,
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp)
        )
    }
}

@Composable
private fun MiniServiceItem(
    miniServices: MiniService,
    modifier: Modifier = Modifier,
) {
    Column(
        modifier
    ) {
        Text(
            text = miniServices.name,
            fontSize = 18.sp,
            fontWeight = FontWeight.Bold,
        )

        Text(
            text = stringResource(
                id = R.string.service_alias,
                miniServices.service_alias
            ),
            fontSize = 14.sp,
            fontWeight = FontWeight.Normal,
            color = Color.Gray
        )
    }
}