# Atividade 02 - Temporizador One Shot para LEDs

Projeto para Raspberry Pi Pico W que controla uma sequência de LEDs com temporização através de um botão, usando callbacks de alarme.

## Requisitos
- VS Code com extensões:
  - Wokwi (para simulação)
  - Raspberry Pi Pico Project (para desenvolvimento)
- Pico SDK 2.1.0
- Toolchain ARM 13.3 Rel1
- Ninja 1.12.1

## Configuração do Hardware (Wokwi)

![Diagrama de conexão](assets\image.png)

Componentes:
- Raspberry Pi Pico W
- 3 LEDs (GPIO11, GPIO12, GPIO13)
- 3 Resistores de 330Ω
- Botão no GPIO5 com resistor pull-up

## Como compilar e executar

1. Clone o repositório:
```bash
git clone https://github.com/coelhoisaque/atividades_02.git
cd atividades-02
```

2. Configure o ambiente:
```bash
mkdir build
cd build
cmake ..
```

3. Compile o projeto:
```bash
make -j4
```

4. Carregue no Pico:
- Monte o Pico em modo BOOTSEL
- Copie `atividades_02.uf2` para a unidade aparecida

## Funcionamento
1. Ao pressionar o botão:
   - Todos LEDs acendem
   - Após 3s: LED vermelho apaga
   - Após mais 3s: LED amarelo apaga
   - Após mais 3s: LED verde apaga

2. O botão só funciona quando todos LEDs estão apagados

## Simulação no Wokwi
1. Abra o VS Code
2. Instale a extensão Wokwi
3. Clique no ícone Wokwi na barra lateral
4. Selecione "Raspberry Pi Pico W" como placa
5. A simulação iniciará automaticamente

## Configuração para BitDogLab
Para usar com o LED RGB e Botão A:
```c
// Pinos originais:
#define LED1_PIN 13   // Verde
#define LED2_PIN 12   // Amarelo 
#define LED3_PIN 11   // Vermelho
#define BUTTON_PIN 5  // Botão A
```

## Estrutura do Projeto
```
atividades_02/
├── CMakeLists.txt
├── pico_sdk_import.cmake
├── atividades_02.c
└── README.md
```

## Licença
MIT License
```

### Validação da Configuração CMake

Seu `CMakeLists.txt` e `pico_sdk_import.cmake` estão corretos. Apenas verifique:

1. Versões compatíveis no `CMakeLists.txt`:
```cmake
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
```

2. Configuração da placa:
```cmake
set(PICO_BOARD pico_w CACHE STRING "Board type")
```

3. Dependências necessárias:
```cmake
target_link_libraries(atividades_02
    pico_stdlib
    hardware_gpio
    hardware_timer
)
```

Adicione as bibliotecas hardware_gpio e hardware_timer no target_link_libraries se necessário.

### Fluxo de Trabalho Recomendado

1. Desenvolvimento no VS Code:
```bash
code atividades_02.c
```

2. Compilação rápida (Ctrl+Shift+B):
```json
// .vscode/tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build",
            "type": "shell",
            "command": "cmake --build build",
            "group": "build"
        }
    ]
}
```

3. Simulação direta com Wokwi:
   - Use o atalho `Ctrl+Shift+P > Wokwi: Start Simulator`

Esta estrutura garantirá que o projeto seja facilmente replicável e atenda todos os requisitos da atividade.