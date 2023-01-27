package cz.cvut.fit.tjv.swordrentalserver.controller;

import cz.cvut.fit.tjv.swordrentalserver.business.AbstractCrudService;
import cz.cvut.fit.tjv.swordrentalserver.business.ContractService;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.ContractDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Contract;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.ContractRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.function.Function;

@RestController
@RequestMapping("/contracts")
public class ContractController extends AbstractCrudController<Contract, ContractDto, ContractRepository> {

    private final ContractService contractService;
    public ContractController(AbstractCrudService<Long, Contract, ContractRepository> service, Function<Contract, ContractDto> toDtoConverter, Function<ContractDto, Contract> toEntityConverter, ContractService contractService) {
        super(service, toDtoConverter, toEntityConverter);
        this.contractService = contractService;
    }

    @PutMapping("/{id}")
    public ResponseEntity<Contract> update(@RequestBody ContractDto contractDto, @PathVariable Long id) {
        return contractService.update(contractDto, id);
    }
}
