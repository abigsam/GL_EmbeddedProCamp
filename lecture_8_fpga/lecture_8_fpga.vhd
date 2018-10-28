
library ieee;
use ieee.std_logic_1164.all;

entity logic_task is
port (
    clk      : in std_logic;
    rst      : in std_logic;
    ce       : in std_logic;
    data_in  : in std_logic_vector(16-1 downto 0);
    data_out : out std_logic_vector(16-1 downto 0);
) end;


architecture rtl of logic_task is

signal in_reg, out_reg, layer_2 : std_logic_vector(16-1 downto 0) := (others => '0');
signal layer_1 : std_logic_vector(7 downto 0) := (others => '0');

begin
    
    -- Non-registered logic, layer #1
    layer_1(0) <= in_reg(0) nor in_reg(1);
    layer_1(1) <= in_reg(2) nor in_reg(3);
    layer_1(2) <= in_reg(4) nor in_reg(5);
    layer_1(3) <= in_reg(6) nor in_reg(7);
    layer_1(4) <= in_reg(8) nor in_reg(9);
    layer_1(5) <= in_reg(10) nor in_reg(11);
    layer_1(6) <= in_reg(12) or in_reg(13);
    layer_1(7) <= in_reg(14) or in_reg(15);
    
    -- Non-registered logic, layer #2
    layer_2(15) = not out_wire(14);
    layer_2(14) = out_wire(13) and layer_1(7);
    layer_2(13) = layer_1(6) nand layer_1(7);
    layer_2(12) = out_wire(13) or not layer_1(6);
    layer_2(11) = not layer_1(6);
    layer_2(10) = not layer_1(5);
    layer_2(9) = out_wire(10) and out_wire(8);
    layer_2(8) = not layer_1(4);
    layer_2(7) = out_wire(8) or layer_1(4);
    layer_2(6) = out_wire(7) and out_wire(5);
    layer_2(5) = layer_1(3) or out_wire(4);
    layer_2(4) = layer_1(3) nor layer_1(2);
    layer_2(3) = out_wire(4) nor (not layer_1(3));
    layer_2(2) = (not out_wire(3)) and out_wire(1);
    layer_2(1) = (not layer_1(1)) or ((not layer_1(1)) nand out_wire(0));
    layer_2(0) = not layer_1(0);
    
    -- Input register
    IN_PROC: process(clk)
    begin
        if rising_edge(clk) then
            if (ce = '1') then
                in_reg  <= data_in;
            end if;
            if (rst = '0') then
                in_reg  <= (others => '0');
            end if;
        end if;
    end process;
    
    -- Output register
    OUT_PROC: process(clk)
    begin
        if rising_edge(clk) then
            out_reg <= layer_2;
            if (rst = '1') then
                out_reg <= (others => '0');
            end if;
        end if;
    end process;
    
    -- Module output
    data_out <= out_reg;
    
end rtl;