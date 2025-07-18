package cz.cvut.fit.tjv.swordrentalserver.app;

import cz.cvut.fit.tjv.swordrentalserver.controller.ContractController;
import cz.cvut.fit.tjv.swordrentalserver.controller.PersonController;
import cz.cvut.fit.tjv.swordrentalserver.controller.SwordController;
import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit.jupiter.SpringExtension;

@ExtendWith(SpringExtension.class)
@SpringBootTest
public class SwordRentalAppTests {

    @Autowired
    ContractController contractController;

    @Autowired
    PersonController personController;

    @Autowired
    SwordController swordController;

    @Test
    public void contextLoadsTests() {
        Assertions.assertThat(contractController).isNotNull();
        Assertions.assertThat(personController).isNotNull();
        Assertions.assertThat(swordController).isNotNull();
    }
}
