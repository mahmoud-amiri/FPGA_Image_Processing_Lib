-- SMPTE 296 M
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;
entity cam_ds_to_axi is
    port (
        iClk         : in std_logic;
        iDs          : in std_logic_vector(15 downto 0);
        m_axi_tdata  : out std_logic_vector(15 downto 0);
        m_axi_tready : in std_logic;
        m_axi_tvalid : out std_logic;
        m_axi_tuser  : out std_logic;
        m_axi_tlast  : out std_logic
    );
end cam_ds_to_axi;

architecture arch of cam_ds_to_axi is

    constant SAV_ACTIVE   : std_logic_vector(7 downto 0) := X"80";
    constant SAV_BLANKING : std_logic_vector(7 downto 0) := X"AB";
    constant EAV_ACTIVE   : std_logic_vector(7 downto 0) := X"9D";
    constant EAV_BLANKING : std_logic_vector(7 downto 0) := X"B6";
    signal sShiftReg      : std_logic_vector(16 * 4 - 1 downto 0);
    signal sSAV_active    : std_logic;
    signal sSAV_blanking  : std_logic;
    signal sEAV_active    : std_logic;
    signal sEAV_active_r  : std_logic;
    signal sEAV_blanking  : std_logic;
    signal sActiveline    : std_logic;
    signal sActiveline_r  : std_logic;
    signal sActiveline_r2 : std_logic;
    signal sActiveline_r3 : std_logic;
    signal sActiveline_r4 : std_logic;
    signal sActiveline_r5 : std_logic;
    signal sBlankingLine  : std_logic;
    signal sRegion        : std_logic;
    signal sRegion_r      : std_logic;
    signal sDs_r          : std_logic_vector(15 downto 0);
    signal sDs_r2         : std_logic_vector(15 downto 0);
    signal sDs_r3         : std_logic_vector(15 downto 0);
    signal sDs_r4         : std_logic_vector(15 downto 0);
    signal sDs_r5         : std_logic_vector(15 downto 0);
    signal sDs_r6         : std_logic_vector(15 downto 0);
    signal sTuser         : std_logic;
    signal sTuser_r       : std_logic;
    signal sTuser_r2      : std_logic;
    signal sTuser_r3      : std_logic;
    signal sTuser_r4      : std_logic;
begin
    process (iClk)
    begin
        if (rising_edge(iClk)) then
            sDs_r  <= iDs;
            sDs_r2 <= sDs_r;
            sDs_r3 <= sDs_r2;
            sDs_r4 <= sDs_r3;
            sDs_r5 <= sDs_r4;
            sDs_r6 <= sDs_r5;
            --------------------------------
            sShiftReg(4 * 16 - 1 downto 3 * 16) <= sShiftReg(3 * 16 - 1 downto 2 * 16);
            sShiftReg(3 * 16 - 1 downto 2 * 16) <= sShiftReg(2 * 16 - 1 downto 1 * 16);
            sShiftReg(2 * 16 - 1 downto 1 * 16) <= sShiftReg(1 * 16 - 1 downto 0 * 16);
            sShiftReg(1 * 16 - 1 downto 0 * 16) <= iDs;
            --------------------------------
            sSAV_active   <= '0';
            sSAV_blanking <= '0';
            sEAV_active   <= '0';
            sEAV_blanking <= '0';
            if (sShiftReg = X"FFFF00000000" & SAV_ACTIVE & SAV_ACTIVE) then
                sSAV_active <= '1';
                sActiveline <= '1';
                sRegion     <= '1';
            end if;

            if (sShiftReg = X"FFFF00000000" & SAV_BLANKING & SAV_BLANKING) then
                sSAV_blanking <= '1';
                sBlankingLine <= '1';
                sRegion       <= '0';
            end if;

            if (sShiftReg = X"FFFF00000000" & EAV_ACTIVE & EAV_ACTIVE) then
                sEAV_active <= '1';
                sActiveline <= '0';
            end if;

            if (sShiftReg = X"FFFF00000000" & EAV_BLANKING & EAV_BLANKING) then
                sEAV_blanking <= '1';
                sBlankingLine <= '0';
            end if;
            --------------------------------
            sActiveline_r  <= sActiveline;
            sActiveline_r2 <= sActiveline_r;
            sActiveline_r3 <= sActiveline_r2;
            sActiveline_r4 <= sActiveline_r3;
            sActiveline_r5 <= sActiveline_r4;
            sTuser         <= '0';
            if ((sSAV_active = '1') and (sRegion_r = '0')) then
                sTuser <= '1';
            end if;
            sTuser_r  <= sTuser;
            sTuser_r2 <= sTuser_r;
            sTuser_r3 <= sTuser_r2;
            sTuser_r4 <= sTuser_r3;
            sRegion_r <= sRegion;
        end if;
    end process;
    m_axi_tvalid <= (sActiveline and sActiveline_r5) or sEAV_active;
    m_axi_tlast  <= sEAV_active;
    m_axi_tdata  <= sDs_r6;
    m_axi_tuser  <= sTuser_r4;
    -- ila_inst : entity work.ila_1
    --     port map(
    --         clk                  => iClk,
    --         probe0(15 downto 0)  => iDs,
    --         probe0(31 downto 16) => sDs_r4,
    --         probe0(95 downto 32) => sShiftReg,
    --         probe0(96)           => sSAV_active,
    --         probe0(97)           => sSAV_blanking,
    --         probe0(98)           => sEAV_active,
    --         probe0(99)           => sEAV_blanking,
    --         probe0(100)          => sActiveline,
    --         probe0(101)          => sRegion,
    --         probe0(102)          => sTuser,
    --         probe0(103)          => sTuser_r3
    --     );
end arch;