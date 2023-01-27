package cz.cvut.fit.tjv.swordrentalserver.controller;

import cz.cvut.fit.tjv.swordrentalserver.business.SwordService;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.converter.DtoToSwordConverter;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.converter.SwordToDtoConverter;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Sword;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.context.annotation.Import;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

import java.util.HashSet;

@Import({SwordToDtoConverter.class, DtoToSwordConverter.class})
@WebMvcTest(SwordControllerTests.class)
public class SwordControllerTests {

    @MockBean
    SwordService swordService;

    @Autowired
    MockMvc mockMvc;

    Sword sword = new Sword(1L, "katana", 214542, 21, 222, new HashSet<>());

    @BeforeEach
    public void setUp() {
        Mockito.when(swordService.create(sword)).thenReturn(sword);
    }

    @Test
    void delete() throws Exception {
        mockMvc.perform(MockMvcRequestBuilders.delete("/swords/2").accept("application/json"))
                .andExpect(MockMvcResultMatchers.status().isNotFound());
    }
}
