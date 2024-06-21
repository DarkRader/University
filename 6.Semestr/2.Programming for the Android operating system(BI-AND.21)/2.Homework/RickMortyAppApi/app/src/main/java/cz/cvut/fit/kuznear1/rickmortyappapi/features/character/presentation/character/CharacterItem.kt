package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.character

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Star
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import coil.compose.AsyncImage
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character

@Composable
fun CharacterItem(character: Character, modifier: Modifier = Modifier) {
    Row(modifier) {
        AsyncImage(
            model = character.imageUrl,
            contentDescription = "ProfileIcon",
            contentScale = ContentScale.Crop,
            modifier = Modifier
                .size(44.dp)
                .clip(RoundedCornerShape(8.dp))
        )
        Spacer(modifier = Modifier.size(8.dp))

        Column {
            Row(
                horizontalArrangement = Arrangement.Start,
                verticalAlignment = Alignment.CenterVertically
            ) {
                Text(
                    text = character.name,
                    fontSize = 20.sp,
                    fontWeight = FontWeight.Bold,
                )
                Spacer(modifier = Modifier.size(10.dp))
                if(character.favourite) {
                    Icon(
                        Icons.Default.Star,
                        contentDescription = "Favourite",
                        modifier = Modifier.size(20.dp),
                        tint = Color.Blue
                    )
                }
            }
            Text(
                text = character.status,
                fontSize = 14.sp,
                fontWeight = FontWeight.Normal,
                color = Color.Gray
            )
        }
    }
}