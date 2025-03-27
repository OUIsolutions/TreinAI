## Cli Usage

### Configure a model
For Configure a model, you just need to call **RagCraft** passing **configure_model** as first argument:

```bash
RagCraft configure_model --model grok-2-latest --url https://api.x.ai/v1/chat/completions   --key "your key"
```

### Start the application
For start the application, you just need to call **RagCraft** passing **start** as first argument:

```bash
RagCraft start
```
### Start the application with a model
For start the application with a model, you just need to call **RagCraft** passing **start** as first argument and the model as second argument:

```bash
RagCraft start --model grok-2-latest
```

### List Models 
to list the models, you just need to call **RagCraft** passing **list_models** as first argument:

```bash
RagCraft list_models
```

### Remove Model

For remove a model, you just need to call **RagCraft** passing **remove_model** as first argument:

```bash
RagCraft remove_model --model grok-2-latest
```

### Set model as Default 
For set a model as default, you just need to call **RagCraft** passing **set_model_as_default** as first argument:

```bash
RagCraft set_model_as_default --model grok-2-latest
```
### Resset Configuration
For resset the configuration, you just need to call **RagCraft** passing **resset** as first argument:

```bash
RagCraft resset
```

### Get Help
For get help, you just need to call **RagCraft** passing **help** as first argument:

```bash
RagCraft help
```
