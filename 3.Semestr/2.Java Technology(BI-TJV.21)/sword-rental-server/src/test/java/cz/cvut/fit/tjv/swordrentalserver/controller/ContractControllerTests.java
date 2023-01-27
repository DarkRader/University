package cz.cvut.fit.tjv.swordrentalserver.controller;

import cz.cvut.fit.tjv.swordrentalserver.business.ContractService;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.converter.ContractToDtoConverter;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.converter.DtoToContractConverter;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Contract;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
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


@Import({ContractToDtoConverter.class, DtoToContractConverter.class})
@WebMvcTest(ContractControllerTests.class)
public class ContractControllerTests {

    @MockBean
    ContractService contractService;

    @Autowired
    MockMvc mockMvc;

    Person person = new Person(1L, new HashSet<>(), "Lucky", "Grabi", "Nanor", 21512, "luckyf@mail.com", new HashSet<>());
    Sword sword = new Sword(1L, "longsword", 2214142, 2, 22, new HashSet<>());
    Contract contract = new Contract(1L, "2023-1-12", 2124, "party", "ship", person, sword);

    @BeforeEach
    public void setUp() {
        Mockito.when(contractService.create(contract)).thenReturn(contract);
    }

    @Test
    void delete() throws Exception {
        mockMvc.perform(MockMvcRequestBuilders.delete("/contracts/2").accept("application/json"))
                .andExpect(MockMvcResultMatchers.status().isNotFound());
    }
}
