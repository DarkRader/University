package cz.cvut.fit.tjv.swordrentalserver.controller;

import cz.cvut.fit.tjv.swordrentalserver.business.PersonService;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.converter.DtoToPersonConverter;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.converter.PersonToDtoConverter;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
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


@Import({PersonToDtoConverter.class, DtoToPersonConverter.class})
@WebMvcTest(PersonControllerTests.class)
class PersonControllerTests {
    @Autowired
    private MockMvc mockMvc;

    @MockBean
    private PersonService personService;
    Person person = new Person(1L, null, "Radi", "Mulan", "Kaligan", 21542212, "kaligafw@mail.com", null);

    @BeforeEach
    public void setUp() {
        Mockito.when(personService.create(person)).thenReturn(person);
    }

    @Test
    void delete() throws Exception {
        mockMvc.perform(MockMvcRequestBuilders.delete("/persons/2").accept("application/json"))
                .andExpect(MockMvcResultMatchers.status().isNotFound());
    }
}
