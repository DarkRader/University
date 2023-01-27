package cz.cvut.fit.tjv.swordrentalserver.data.repository;

import cz.cvut.fit.tjv.swordrentalserver.data.entity.Contract;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Sword;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;

import java.util.Arrays;
import java.util.Collection;
import java.util.HashSet;

import static org.assertj.core.api.AssertionsForInterfaceTypes.assertThat;

@DataJpaTest
class ContractRepositoryTest {

    private final ContractRepository contractRepository;
    private final SwordRepository swordRepository;
    private final PersonRepository personRepository;

    @Autowired
    ContractRepositoryTest(ContractRepository contractRepository, SwordRepository swordRepository, PersonRepository personRepository) {
        this.contractRepository = contractRepository;
        this.swordRepository = swordRepository;
        this.personRepository = personRepository;
    }

    @BeforeEach
    void clearDB() {
        contractRepository.deleteAll();
    }

    @Test
    void findAllByPerson() {
        Person person = new Person(1L, new HashSet<>(), "Lucky", "Grabi", "Nanor", 21512, "luckyf@mail.com", new HashSet<>());

        Sword sword1 = new Sword(1L, "longsword", 2214142, 2, 22, new HashSet<>());
        Contract contract1 = new Contract(1L, "2023-1-12", 2124, "party", "ship", person, sword1);

        Sword sword2 = new Sword(2L, "longsword", 2214142, 2, 22, new HashSet<>());
        Contract contract2 = new Contract(2L, "2023-1-13", 24, "pary", "car", person, sword2);

        personRepository.save(person);

        swordRepository.save(sword1);
        contractRepository.save(contract1);

        swordRepository.save(sword2);
        contractRepository.save(contract2);

        Collection<Contract> expected = Arrays.asList(contract1, contract2);
        Collection<Contract> actual = contractRepository.findAllByPerson(person);

        assertThat(actual).hasSameElementsAs(expected);
    }
}