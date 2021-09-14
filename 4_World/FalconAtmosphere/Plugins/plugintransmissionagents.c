modded class PluginTransmissionAgents
{
	void PluginTransmissionAgents()
	{
		RegisterAgent(new RadiationAgent);
		RegisterAgent(new SleepAgent);
	}
}